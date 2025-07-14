import Player from "./components/Player.jsx";
import TimerChallenge from "./components/TimerChallenge.jsx";

function App() {
  return (
    <>
      <Player />
      <div id="challenges">
        <TimerChallenge title="Easy" targetTimeSec={1} />
        <TimerChallenge title="Not so easy" targetTimeSec={5} />
        <TimerChallenge title="Hard...?" targetTimeSec={10} />
        <TimerChallenge title="Only if you dare" targetTimeSec={15} />
      </div>
    </>
  );
}

export default App;
