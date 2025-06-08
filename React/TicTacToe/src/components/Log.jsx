export default function Log({ gameTurns }) {
  let log = [];
  for (const turn of gameTurns) {
    const { square, player } = turn;
    const { row, col } = square;

    log.push(
      <li key={`${row}${col}`}>
        Player {player} chose square [{row},{col}]
      </li>
    );
  }

  return <ol id="log">{log}</ol>;
}
