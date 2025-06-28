# Unreal Engine Skill Tree UI System

This project implements a modular, hold-to-unlock skill tree in Unreal Engine 5 using C++ and UMG.

---

## 📦 Components Overview

### `USkillTree`
The main widget that creates and manages skill buttons.

- Dynamically creates buttons using `NodeLabels` and `NodeCosts`.
- Ensures default costs are applied if some are missing.
- Unlocks buttons sequentially.
- Deducts player money on unlock and updates the menu display.

### `USkillTreeButton`
An individual skill node with hold-to-unlock logic.

- Displays the skill label and cost.
- Requires a button press to be held for `MaxHoldTime`.
- Displays progress bar while holding.
- Unlocks itself and triggers the next skill if player has enough funds.
- Turns green when unlocked; flashes red when funds are insufficient.

### `USkillTreeMenu`
The parent menu UI that contains the skill tree.

- Displays player money.
- Updates whenever a skill is unlocked.

---

## 🔁 Skill Unlock Flow

1. On construction, the `SkillTree` spawns buttons for each node.
2. The first button is enabled, others are locked.
3. Player holds a button:
   - Progress bar fills over time.
   - When full:
     - If funds are enough → unlocks, deducts money, enables next.
     - If not → flashes red, stays locked.
4. Button color and state visually reflect unlock status.

---

## 🎮 Input Handling

Press E to toggle the menu on / off

## ✅ To Do

    Add support for branching skill trees (dependencies).

    Save/load skill tree state.

    Add animations or SFX for feedback.
