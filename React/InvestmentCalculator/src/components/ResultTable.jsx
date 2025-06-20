import { calculateInvestmentResults, formatter } from "../util/investment";

function createResultDataRows(annualData) {
  return annualData.map((row, index) => (
    <tr key={row.year}>
      <td>{row.year}</td>
      <td>{formatter.format(row.annualInvestment)}</td>
      <td>{formatter.format(row.interest)}</td>
      <td>{formatter.format(row.annualInvestment - row.valueEndOfYear)}</td> 
      <td>{formatter.format(row.valueEndOfYear)}</td>
    </tr>
  ));
}

export default function ResultTable(
  initialInvestment,
  annualInvestment,
  expectedReturn,
  duration
) {
  const annualData = calculateInvestmentResults(
    initialInvestment,
    annualInvestment,
    expectedReturn,
    duration
  );

  console.log(annualData);

  return (
    <table id="result">
      <thead>
        <tr>
          <th>Year</th>
          <th>Investment Value</th>
          <th>Intrest (Year)</th>
          <th>Total Intrest</th>
          <th>Invested Capital</th>
        </tr>
      </thead>
      <tbody>{createResultDataRows(annualData)}</tbody>
    </table>
  );
}
