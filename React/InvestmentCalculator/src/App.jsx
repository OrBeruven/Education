import { useState } from "react";

import UserInput from "./components/UserInput";
import ResultTable from "./components/ResultTable";

const DEFAULT_USER_INPUT = {
  initial: 0,
  annual: 0,
  returnRate: 0,
  duration: 0,
};

function App() {
  const [userInput, setUserInput] = useState(DEFAULT_USER_INPUT);

  function handleInputChange(event) {
    const id = event.target.id;
    const newValue = event.target.value;

    setUserInput((prev) => {
      const updatedInput = {...prev};
      updatedInput[id] = newValue;
      return updatedInput;
    });
  }

  console.log(userInput);
  return (
    <>
      <UserInput onChange={handleInputChange}></UserInput>
      <ResultTable
        initialInvestment={userInput["initial"]}
        annualInvestment={userInput["annual"]}
        expectedReturn={userInput["returnRate"]}
        duration={userInput["duration"]}
      ></ResultTable>
    </>
  );
}

export default App;
