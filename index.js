const minesweeper = require("./build/Release/minesweeper.node");

const instance = new minesweeper.EngineApi(10, 10, 4)

console.log(instance)
console.log(instance.isGameOver())
