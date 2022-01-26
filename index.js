const minesweeper = require("./build/Release/minesweeper.node");

const instance = new minesweeper.EngineApi(10, 10, 4)
const fullBoard = instance.getFullBoard()
console.log(instance)
console.log(instance.isGameOver())
console.log(fullBoard)
console.log(instance.getState())
