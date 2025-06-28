# Skill Tree UI System (Unreal Engine 5)

# 

# This system implements a modular, hold-to-unlock skill tree in Unreal Engine 5 using UMG widgets and C++. It includes:

# 

# &nbsp;   A SkillTree widget managing multiple skill buttons.

# 

# &nbsp;   SkillTreeButton UI elements that must be held to unlock.

# 

# &nbsp;   A SkillTreeMenu that updates and displays player money.

# 

# &nbsp;   Support for chaining skills and visual feedback (color, progress bar, and cost labels).

# 

# 📦 Components Overview

# USkillTree

# 

# &nbsp;   Manages a dynamic list of skill buttons.

# 

# &nbsp;   Handles player money deduction and progression unlocking.

# 

# &nbsp;   Controls visibility and communicates with its parent SkillTreeMenu.

# 

# Important Properties

# 

# &nbsp;   NodeLabels: List of skill names.

# 

# &nbsp;   NodeCosts: Cost of each skill.

# 

# &nbsp;   SkillTreeButtonClass: Class for creating individual skill buttons.

# 

# &nbsp;   ButtonContainer: Vertical box holding buttons.

# 

# &nbsp;   PlayerChar: Cached reference to the owning character.

# 

# USkillTreeButton

# 

# &nbsp;   Individual button representing a skill node.

# 

# &nbsp;   Requires the player to hold the button to unlock.

# 

# &nbsp;   Visuals include progress bar, cost label, and feedback on unlock/failure.

# 

# Key Features

# 

# &nbsp;   Green button = unlocked.

# 

# &nbsp;   Red flash = insufficient funds.

# 

# &nbsp;   Progress bar shows hold duration.

# 

# USkillTreeMenu

# 

# &nbsp;   Container UI holding the SkillTree and player money text.

# 

# &nbsp;   On NativeConstruct, binds to the player character and updates money display.

# 

# 🔁 Skill Unlock Flow

# 

# &nbsp;   Skill tree spawns buttons based on NodeLabels.

# 

# &nbsp;   Only the first skill button is enabled at the start.

# 

# &nbsp;   Player holds a button → progress bar fills.

# 

# &nbsp;   On completion:

# 

# &nbsp;       If enough funds → unlocks button and enables the next one.

# 

# &nbsp;       If not enough funds → flashes red.

# 

# &nbsp;   UI updates player’s available money in real time.

# 

# 🧠 Input + Widget Control

# 

# In the character:

# 

# SkillTreeInstance = CreateWidget<UUserWidget>(...);

# SkillTreeInstance->AddToViewport();

# 

# FInputModeGameAndUI InputMode;

# InputMode.SetWidgetToFocus(SkillTreeInstance->TakeWidget());

# PlayerController->SetInputMode(InputMode);

# PlayerController->bShowMouseCursor = true;

# 

# To hide without destroying:

# 

# SkillTreeInstance->SetVisibility(ESlateVisibility::Hidden);

# 

# 💡 Notes

# 

# &nbsp;   NodeCosts will automatically pad missing entries with a default cost.

# 

# &nbsp;   The progress bar and unlock animation are handled entirely in the button itself.

# 

# &nbsp;   You can reuse SkillTree in multiple menus since it doesn’t hardcode player refs.

# 

# &nbsp;   Button styling (green/red) uses Slate brush manipulation.

