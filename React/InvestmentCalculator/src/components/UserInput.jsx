export default function UserInput({onChange}) {
  return (
    <section id="user-input">
      <div className="input-group">
        <p>
          <label htmlFor="initial">Initial Investment</label>
          <input type="number" id="initial" onChange={onChange} />
        </p>
        <p>
          <label htmlFor="annual">Annual Investment</label>
          <input type="number" id="annual" onChange={onChange} />
        </p>
      </div>
      <div className="input-group">
        <p>
          <label htmlFor="returnRate">Expected Return (%)</label>
          <input type="number" id="returnRate" onChange={onChange} />
        </p>
        <p>
          <label htmlFor="duration">Duration (Years)</label>
          <input type="number" id="duration" onChange={onChange} />
        </p>
      </div>
    </section>
  );
}
