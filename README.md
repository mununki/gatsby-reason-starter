# A starter of Gatsby + ReasonML

## How to add the ReasonML(based on `ReScript` toolchain)

### Install dependencies

```shell
$ npm i bs-platform reason-react
```

### Create `bsconfig.json`

```json
{
  "name": "your-project-name",
  "reason": {
    "react-jsx": 3
  },
  "bsc-flags": ["-bs-super-errors"],
  "sources": [
    {
      "dir": "src",
      "subdirs": true
    }
  ],
  "package-specs": [
    {
      "module": "es6",
      "in-source": true
    }
  ],
  "suffix": ".bs.js",
  "namespace": true,
  "bs-dependencies": ["reason-react"],
  "ppx-flags": [],
  "refmt": 3
}
```

### Add scripts in `package.json`

```json
  ...
  "re:build": "bsb -make-world -clean-world",
  "re:watch": "bsb -make-world -clean-world -w"
  ...
```

## How to run (dev mode)

### Run `bsb` in watch mode

```shell
$ npm run re:watch
```

### Run Gatsby in dev mode

```shell
$ npm run develop
```

## How to build to static

### Build `*.re`

```shell
$ npm run re:build
```

### Build Gatsby

```shell
$ npm run build
```