[@react.component]
let make = () => {
  <ApolloClient.React.ApolloProvider client=Apollo.instance>
    <Greeting />
  </ApolloClient.React.ApolloProvider>;
};
