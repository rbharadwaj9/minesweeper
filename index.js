const minesweeper = require("./build/Release/minesweeper.node");

const instance = new minesweeper.EngineApi(10, 10, 4)
const fullBoard = instance.getFullBoard()
console.log(instance)
console.log("Mines:")
console.log(instance.getMines())
console.log(instance.isGameOver())
console.log(fullBoard)
console.log(instance.getState())

console.log("Play move 0, 0")
instance.playMove(0, 0)
console.log(instance.getState())
