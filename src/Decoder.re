type obj = {
  name: string,
  scripts: Js.Dict.t(string),
  version: string,
};

let convertScripts = dict : list(Types.script) =>
  Array.to_list(Js.Dict.entries(dict));

let convertRecord = obj : Types.package => {
  name: obj.name,
  version: obj.version,
  scripts: convertScripts(obj.scripts),
  search: "node"
};

module Decode = {
  let obj = json =>
    Json.Decode.{
      name: json |> field("name", string),
      scripts: json |> field("scripts", dict(string)),
      version: json |> field("version", string),
    };
};

let maybeDecode = maybeData =>
  switch (maybeData) {
  | Some(data) => Some(convertRecord(Decode.obj(data)))
  | _ => None
  };

let decodedData = data => data |> Json.parse |> maybeDecode;