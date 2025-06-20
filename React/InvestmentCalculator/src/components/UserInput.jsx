export default function UserInput({ userInput, onChange }) {
  const isDurationValid =
    Number.isInteger(userInput.duration) && userInput.duration > 0;

  return (
    <section id="user-input">
      <div className="input-group">
        <p>
          <label htmlFor="initial">Initial Investment</label>
          <input
            type="number"
            id="initial"
            value={userInput.initial}
            onChange={onChange}
          />
        </p>
        <p>
          <label htmlFor="annual">Annual Investment</label>
          <input
            type="number"
            id="annual"
            value={userInput.annual}
            onChange={onChange}
          />
        </p>
      </div>
      <div className="input-group">
        <p>
          <label htmlFor="returnRate">Expected Return (%)</label>
          <input
            type="number"
            id="returnRate"
            value={userInput.returnRate}
            onChange={onChange}
          />
        </p>
        <p>
          <label htmlFor="duration">Duration (Years)</label>
          <input
            type="number"
            id="duration"
            value={userInput.duration}
            onChange={onChange}
          />
        </p>
      </div>

      {!isDurationValid && (
        <p className="error">
          Please enter a valid duration (Greater than 0).
        </p>
      )}
    </section>
  );
}
