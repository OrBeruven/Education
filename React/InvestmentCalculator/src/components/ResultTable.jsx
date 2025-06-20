import { calculateInvestmentResults, formatter } from "../util/investment";

function createResultDataRows(annualData) {
  const initialInvestment =
    annualData[0].valueEndOfYear -
    annualData[0].interest -
    annualData[0].annualInvestment;

  return annualData.map((yearData) => {
    const totalIntrest =
      yearData.valueEndOfYear -
      yearData.annualInvestment * yearData.year -
      initialInvestment;
    const totalAmountInvested = yearData.valueEndOfYear - totalIntrest;

    return (
      <tr key={yearData.year}>
        <td>{yearData.year}</td>
        <td>{formatter.format(yearData.valueEndOfYear)}</td>
        <td>{formatter.format(yearData.interest)}</td>
        <td>{formatter.format(totalIntrest)}</td>
        <td>{formatter.format(totalAmountInvested)}</td>
      </tr>
    );
  });
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
