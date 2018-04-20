open Node;
open Types;

let makePath = (cwd: string) : string => cwd ++ "/package.json";

let exists = (path: string) => Fs.existsSync(path);

let openPackage = (path: string) : option(string) =>
  exists(path) ? Some(Fs.readFileAsUtf8Sync(path)) : None;

let json = openPackage(makePath(Process.cwd()));

Js.log(Chalk.red("Found a package.json?"));

switch (json) {
| Some(file) => Js.log(Chalk.yellow(file))
| _ => ()
};

let defaultState: package = {
  name: "Not found",
  version: "0.0.0",
  search: "clean",
  scripts: []
};

let package: package =
  switch (json) {
  | Some(text) =>
    let maybePackage = Decoder.decodedData(text);
    switch (maybePackage) {
    | Some(pack) => pack
    | _ => defaultState
    };
  | _ => defaultState
  };


Js.log(
  Chalk.red(package.name) ++ " version " ++ Chalk.yellow(package.version),
);
/*List.iter(Js.log, package.scripts);*/

let filtered = Filter.getFilteredScripts(package.search, package.scripts);
List.iter(Js.log, filtered);