type obj = {
  name: string,
  scripts: Js.Dict.t(string),
};

let convertScripts = dict : list(Types.script) =>
  Array.to_list(Js.Dict.entries(dict));

let convertRecord = obj : Types.package => {
  name: obj.name,
  scripts: convertScripts(obj.scripts),
};

module Decode = {
  let obj = json =>
    Json.Decode.{
      name: json |> field("name", string),
      scripts: json |> field("scripts", dict(string)),
    };
};

let maybeDecode = maybeData =>
  switch (maybeData) {
  | Some(data) => Some(convertRecord(Decode.obj(data)))
  | _ => None
  };

let decodedData = data => data |> Json.parse |> maybeDecode;