class ActionLicenceCrafting: ActionInteractBase
{
    void ActionLicenceCrafting() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#start_crafting";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item ) {
		DZLLicence licence = player.GetLicenceByPosition();
		if (!licence) return false;

		string message = player.CanUseLicence(licence);

		return !message;
	}

	override void OnStartClient(ActionData action_data) {
	    super.OnStartClient(action_data);
	    GetGame().GetUIManager().ShowScriptedMenu(action_data.m_Player.GetProgressBar(), NULL);
	}
};