import { useRef, useImperativeHandle } from "react";
import { createPortal } from "react-dom";

function convertMillisecondsToSeconds(timeInMilliseconds) {
  return (timeInMilliseconds / 1000).toFixed(2);
}

function calculateScore(timeRemainingMs, targetTimeSec) {
  return Math.round((1 - timeRemainingMs / (targetTimeSec * 1000)) * 100);
}

export default function ResultModal({
  ref,
  timeRemainingMs,
  targetTimeSec,
  onReset,
}) {
  const dialog = useRef();

  const isUserLost = timeRemainingMs <= 0;
  const score = calculateScore(timeRemainingMs, targetTimeSec);

  useImperativeHandle(ref, () => {
    return {
      open() {
        dialog.current.showModal();
      },
    };
  });

  return createPortal(
    <dialog ref={dialog} className="result-modal" onClose={onReset}>
      {isUserLost && <h2 className="lost">You Lost</h2>}
      {!isUserLost && <h2 className="score">Your Score: {score}</h2>}
      <p>
        The target time was <strong>{targetTimeSec} seconds.</strong>
      </p>
      <p>
        You stopped the timer with{" "}
        <strong>
          {convertMillisecondsToSeconds(timeRemainingMs)} seconds left.
        </strong>
      </p>
      <form method="dialog" onSubmit={onReset}>
        <button>Close</button>
      </form>
    </dialog>,
    document.getElementById('modal')
  );
}
