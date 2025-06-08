function isSquareSelected(playerSymbol) {
  return playerSymbol !== null;
}

export default function GameBoard({ onSelectedSquare, gameBoard }) {
  return (
    <ol id="game-board">
      {gameBoard.map((row, rowIndex) => (
        <li key={rowIndex}>
          <ol>
            {row.map((playerSymbol, colIndex) => (
              <li key={colIndex}>
                <button
                  onClick={() => onSelectedSquare(rowIndex, colIndex)}
                  disabled={isSquareSelected(playerSymbol)}
                >
                  {playerSymbol}
                </button>
              </li>
            ))}
          </ol>
        </li>
      ))}
    </ol>
  );
}
