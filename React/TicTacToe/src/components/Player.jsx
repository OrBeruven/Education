import { useState } from "react";

export default function Player({ initialName, symbol }) {
    const [ isEditing, setIsEditing ] = useState(false);
    const [ playerName, setPlayerName] = useState(initialName);

    function handleEditClick() {
        setIsEditing(isEditing => !isEditing);
    }

    function handleChangePlayerName(event) {
        setPlayerName(event.target.value);
    }

    let editablePlayerName = <span className="player-name">{playerName}</span>;
    if (isEditing){
        editablePlayerName = <input type="text" required value={playerName} onChange={handleChangePlayerName} />
    }

    return (
        <li>
            <span className="player">
                {editablePlayerName}
                <span className="player-symbol">{symbol}</span>
            </span>
            <button onClick={handleEditClick}>{isEditing ? "Save" : "Edit"}</button>
        </li>
    );
}