open Node;

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

let decoded =
  switch (json) {
  | Some(text) =>
    let maybePackage = Decoder.decodedData(text);
    switch (maybePackage) {
    | Some(pack) =>
      Js.log(
        Chalk.red(pack.name) ++ " version " ++ Chalk.yellow(pack.version),
      );
      List.iter(Js.log, pack.scripts);
    | _ => Js.log("Could not decode")
    };
  | _ => ()
  };