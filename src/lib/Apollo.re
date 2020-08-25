[%raw "require('es6-promise')"];
[%raw "require('isomorphic-fetch')"];

let graphqlEndpoint = "http://localhost:8070/query";
let graphqlWSEndpoint = "http://localhost:8070/ws";

let headers = () => {
  // TODO: get a token from localStorage
  let token = "12345";
  {
    "headers": {
      "authorization": "Bearer " ++ token,
    },
  };
};

let httpLink =
  ApolloClient.Link.HttpLink.make(
    ~uri=_ => graphqlEndpoint,
    ~headers=Obj.magic(headers),
    (),
  );

// let wsLink =
//   ApolloClient.Link.WebSocketLink.(
//     make(
//       ~uri="ws://" ++ graphqlEndpoint,
//       ~options=
//         ClientOptions.make(
//           ~connectionParams=ConnectionParams(Obj.magic(headers)),
//           ~reconnect=true,
//           (),
//         ),
//       (),
//     )
//   );

let terminatingLink =
  ApolloClient.Link.split(
    ~test=
      ({query}) => {
        let definition = ApolloClient.Utilities.getOperationDefinition(query);
        switch (definition) {
        | Some({kind, operation}) =>
          kind === "OperationDefinition" && operation === "subscription"
        | None => false
        };
      },
    // TODO: must implement & replace with wsLink with WsImplementation
    ~whenTrue=httpLink,
    ~whenFalse=httpLink,
  );

let instance =
  ApolloClient.(
    make(
      ~cache=Cache.InMemoryCache.make(),
      ~connectToDevTools=true,
      ~defaultOptions=
        DefaultOptions.make(
          ~mutate=
            DefaultMutateOptions.make(
              ~awaitRefetchQueries=true,
              ~errorPolicy=All,
              (),
            ),
          ~query=
            DefaultQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~watchQuery=
            DefaultWatchQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          (),
        ),
      ~link=terminatingLink,
      (),
    )
  );
