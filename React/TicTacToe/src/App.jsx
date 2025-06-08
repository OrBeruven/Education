import { useState } from "react";

import Player from "./components/Player.jsx";
import GameBoard from "./components/GameBoard.jsx";
import Log from "./components/Log.jsx";
import GameOver from "./components/GameOver.jsx";
import { WINNING_COMBINATIONS } from "./winning-combinations.js";

const initialGameBoard = [
  [null, null, null],
  [null, null, null],
  [null, null, null],
];

function getCurrentPlayer(gameTurns) {
  let currentPlayer = "X";

  if (gameTurns.length > 0 && gameTurns[0].player === "X") {
    currentPlayer = "O";
  }

  return currentPlayer;
}

function App() {
  const [gameTurns, setGameTurns] = useState([]);
  const [players, setPlayers] = useState({
    X: "Player 1",
    O: "Player 2",
  });

  const activePlayer = getCurrentPlayer(gameTurns);

  let gameBoard = [...initialGameBoard.map((col) => [...col])];

  for (const turn of gameTurns) {
    const { square, player } = turn;
    const { row, col } = square;

    gameBoard[row][col] = player;
  }

  let winner;

  for (const combination of WINNING_COMBINATIONS) {
    const firstSelectedSymbol =
      gameBoard[combination[0].row][combination[0].column];
    const secondSelectedSymbol =
      gameBoard[combination[1].row][combination[1].column];
    const thirdSelectedSymbol =
      gameBoard[combination[2].row][combination[2].column];

    if (
      firstSelectedSymbol &&
      firstSelectedSymbol === secondSelectedSymbol &&
      firstSelectedSymbol === thirdSelectedSymbol
    ) {
      winner = players[firstSelectedSymbol];
    }
  }

  const isADraw = gameTurns.length === 9 && !winner;

  function handleSquareSelected(rowIndex, colIndex) {
    setGameTurns((prevTurns) => {
      const currentPlayer = getCurrentPlayer(prevTurns);

      const updatedTurns = [
        { square: { row: rowIndex, col: colIndex }, player: currentPlayer },
        ...prevTurns,
      ];

      return updatedTurns;
    });
  }

  function handleOnRestart() {
    setGameTurns([]);
  }

  function handleNameChange(playerSymbol, playerName) {
    setPlayers((prevPlayers) => {
      return {
        ...prevPlayers,
        [playerSymbol]: playerName,
      };
    });
  }

  return (
    <main>
      <div id="game-container">
        <ol id="players" className="highlight-player">
          <Player
            initialName="Player 1"
            symbol="X"
            isActive={activePlayer === "X"}
            onPlayerNameChange={handleNameChange}
          />
          <Player
            initialName="Player 2"
            symbol="O"
            isActive={activePlayer === "O"}
            onPlayerNameChange={handleNameChange}
          />
        </ol>
        {(winner || isADraw) && (
          <GameOver winner={winner} onRestart={handleOnRestart} />
        )}
        <GameBoard
          onSelectedSquare={handleSquareSelected}
          selectedPlayerSymbol={activePlayer}
          gameBoard={gameBoard}
        />
      </div>
      <Log gameTurns={gameTurns} />
    </main>
  );
}

export default App;
