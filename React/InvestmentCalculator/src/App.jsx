import { useState } from "react";

import UserInput from "./components/UserInput";
import ResultTable from "./components/ResultTable";

const DEFAULT_USER_INPUT = {
  initial: 10000,
  annual: 1200,
  returnRate: 6,
  duration: 10,
};

function App() {
  const [userInput, setUserInput] = useState(DEFAULT_USER_INPUT);

  function handleInputChange(event) {
    const id = event.target.id;
    const newValue = event.target.value;

    setUserInput((prev) => {
      const updatedInput = { ...prev };
      updatedInput[id] = Number(newValue);
      return updatedInput;
    });
  }

  return (
    <>
      <UserInput userInput={userInput} onChange={handleInputChange}></UserInput>

      <ResultTable
        initialInvestment={userInput.initial}
        annualInvestment={userInput.annual}
        expectedReturn={userInput.returnRate}
        duration={userInput.duration}
      ></ResultTable>
    </>
  );
}

export default App;
