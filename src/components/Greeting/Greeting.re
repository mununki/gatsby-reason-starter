module GetStores = [%graphql
  {|
  query GetStores($skip:Int!, $take:Int!) {
    getStores(skip:$skip, take:$take){
      ok
      error
      stores{
        id
        name
      }
    }
  }
|}
];

[@react.component]
let make = () => {
  switch (GetStores.use(GetStores.makeVariables(~skip=0, ~take=10, ()))) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(error)} =>
    ("Error loading data" ++ error.message)->React.string
  | {data: Some({getStores})} =>
    <div>
      {switch (getStores.ok) {
       | false => React.null
       | true =>
         switch (getStores.stores) {
         | None => React.null
         | Some(stores) =>
           stores
           ->Belt.Array.map(store => {
               switch (store) {
               | None => <String text="" />
               | Some(s) => <p> <String text={s.name} /> </p>
               }
             })
           ->ReasonReact.array
         }
       }}
    </div>
  | {data: None, error: None, loading: false} =>
    "Something bad happened!"->React.string
  };
};
