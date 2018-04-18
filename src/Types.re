type name = string;

type command = string;

type script = (name, command);

type package = {
  name: string,
  scripts: list(script),
};