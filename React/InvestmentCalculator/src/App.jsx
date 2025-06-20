import { useState } from "react";

import UserInput from "./components/UserInput";
import ResultTable from "./components/ResultTable";

const DEFAULT_USER_INPUT = {
  initial: "10000",
  annual: '1200',
  returnRate: "6",
  duration: "10",
};

function App() {
  const [userInput, setUserInput] = useState(DEFAULT_USER_INPUT);

  function handleInputChange(id, newValue) {
    setUserInput((prev) => {
      const updatedInput = { ...prev };
      updatedInput[id] = newValue;
      return updatedInput;
    });
  }

  const isInputValid = Number(userInput.duration) >= 1;

  console.log(isInputValid);

  return (
    <>
      <UserInput userInput={userInput} onChange={handleInputChange}></UserInput>

      {!isInputValid && (
        <p className="error">
          Please enter a valid duration (whole number greater than 0).
        </p>
      )}

      {isInputValid &&
        <ResultTable
          initialInvestment={Number(userInput.initial)}
          annualInvestment={Number(userInput.annual)}
          expectedReturn={Number(userInput.returnRate)}
          duration={Number(userInput.duration)}
        ></ResultTable>}
      
    </>
  );
}

export default App;
