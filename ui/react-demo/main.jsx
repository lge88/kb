var states = [
  'Alabama',
  'Alaska',
  'Arizona',
  'Arkansas',
  'California',
  'Colorado',
  'Connecticut',
  'Delaware',
  'Florida',
  'Georgia',
  'Hawaii',
  'Idaho',
  'Illinois',
  'Indiana',
  'Iowa',
  'Kansas',
  'Kentucky',
  'Louisiana',
  'Maine',
  'Maryland',
  'Massachusetts',
  'Michigan',
  'Minnesota',
  'Mississippi',
  'Missouri',
  'Montana',
  'Nebraska',
  'Nevada',
  'New Hampshire',
  'New Jersey',
  'New Mexico',
  'New York',
  'North Carolina',
  'North Dakota',
  'Ohio',
  'Oklahoma',
  'Oregon',
  'Pennsylvania',
  'Rhode Island',
  'South Carolina',
  'South Dakota',
  'Tennessee',
  'Texas',
  'Utah',
  'Vermont',
  'Virginia',
  'Washington',
  'West Virginia',
  'Wisconsin',
  'Wyoming',
];

class SearchBar extends React.Component {
  render() {
    var query = this.props.query;
    return (
      <input id="input1" type="text"
             value={query}
             onChange={this.handleOnChange.bind(this)}/>
    );
  }

  handleOnChange(e) {
    var updateQuery = this.props.updateQuery;
    updateQuery(e.target.value);
  }
}

class CandidateList extends React.Component {
  render() {
    var candidates = this.props.candidates;
    var lis = candidates.map(function(cand) {
      return (<li key = {cand} > { cand } </li>);
    });

    return (
      <div className="candidates">
        <ul> {lis} </ul>
      </div>
    );
  }
}

class TypeAhead extends React.Component {
  constructor() {
    super();
    this.state = {
      query: '',
      candidates: states.slice(0, 10)
    };
  }

  updateQuery(newQuery) {
    var newCandidates = states.filter(function(state) {
      return state.toLowerCase().indexOf(newQuery) == 0;
    });
    this.setState({
      query: newQuery,
      candidates: newCandidates
    });
  }

  render() {
    return (
      <div className="typeahead">
        <SearchBar query = { this.state.query } updateQuery = { this.updateQuery.bind(this) } />
        <CandidateList candidates = { this.state.candidates } />
      </div>
    );
  }
}

var root = ReactDOM.render(
  <TypeAhead />,
  document.getElementById('root')
);
