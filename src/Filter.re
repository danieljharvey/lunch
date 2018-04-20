open Types;

let stringContains = (needle: string, haystack: string): bool => {
    let matchString = String.trim(
        String.map(char => {
            (String.contains(haystack, char)) ? char : ' ';
        }, needle)
    );
    let length = String.length(matchString) - String.length(needle);
    length >= 0;
};

let packageInSearch = (search: string, script: script): bool => {
    let (name, command) = script;
    stringContains(search, name) || stringContains(search, command);
}; 

let getFilteredScripts = (search: string, scripts: list(script)): list(script) => {
    List.filter(packageInSearch(search), scripts);
}; 