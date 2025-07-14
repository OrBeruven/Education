import { useState, useRef } from "react";
import ResultModal from "./ResultModal";

function convertSecondsToMilliseconds(timeInSecods) {
  return timeInSecods * 1000;
}

export default function TimerChallenge({ title, targetTimeSec }) {
  const timer = useRef();
  const resultDialog = useRef();

  const [timeRemaining, setTimeRemaining] = useState(
    convertSecondsToMilliseconds(targetTimeSec)
  );

  let timerIsActive =
    timeRemaining > 0 &&
    timeRemaining < convertSecondsToMilliseconds(targetTimeSec);

  if (timeRemaining <= 0) {
    clearInterval(timer.current);
    resultDialog.current.open();
    timerIsActive = false;
  }

  function handleReset() {
    setTimeRemaining(convertSecondsToMilliseconds(targetTimeSec));
  }

  function handleStartTimer() {
    timer.current = setInterval(() => {
      setTimeRemaining((prevTimeRemaining) => prevTimeRemaining - 10);
    }, 10);
  }

  function handleStopTimer() {
    clearInterval(timer.current);
    resultDialog.current.open();
  }

  return (
    <>
      <ResultModal
        ref={resultDialog}
        targetTimeSec={targetTimeSec}
        timeRemainingMs={timeRemaining}
        onReset={handleReset}
      />
      <section className="challenge">
        <h2>{title}</h2>
        <p className="challenge-time">
          {targetTimeSec} second{targetTimeSec > 1 ? "s" : ""}
        </p>
        <p>
          <button onClick={timerIsActive ? handleStopTimer : handleStartTimer}>
            {timerIsActive ? "Stop" : "Start"} Challenge
          </button>
        </p>
        <p className={timerIsActive ? "active" : undefined}>
          {timerIsActive ? "Timer is running..." : "Timer Inactive"}
        </p>
      </section>
    </>
  );
}
