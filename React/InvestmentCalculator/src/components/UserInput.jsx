export default function UserInput({ userInput, onChange }) {
  return (
    <section id="user-input">
      <div className="input-group">
        <p>
          <label>Initial Investment</label>
          <input
            type="number"
            id="initial"
            value={userInput.initial}
            onChange={(event) => onChange(event.target.id, event.target.value)}
            required
          />
        </p>
        <p>
          <label>Annual Investment</label>
          <input
            type="number"
            id="annual"
            value={userInput.annual}
            onChange={(event) => onChange(event.target.id, event.target.value)}
            required
          />
        </p>
      </div>
      <div className="input-group">
        <p>
          <label>Expected Return (%)</label>
          <input
            type="number"
            id="returnRate"
            value={userInput.returnRate}
            onChange={(event) => onChange(event.target.id, event.target.value)}
            required
          />
        </p>
        <p>
          <label>Duration (Years)</label>
          <input
            type="number"
            id="duration"
            value={userInput.duration}
            onChange={(event) => onChange(event.target.id, event.target.value)}
            required
          />
        </p>
      </div>
    </section>
  );
}
