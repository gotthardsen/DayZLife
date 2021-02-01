class ActionRobBank: ActionInteractBase
{
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().bankConfig;
        }

        return config;
    }

	void ActionRobBank() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#rob_bank";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsClient()) {
		    if (!player.config) return false;
			config = player.config.bankConfig;
		} else {
		    if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
			GetConfig();
		}
		
		if (config) {
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source) return false;

			bool hasItem = false;
			foreach (string itemForRaid: config.itemsCanUsedToRaidBank) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;
			return isInNearOfBankAndLocationIsEnabled(player));

		}

		return false;
	}

	override void OnStartClient(ActionData action_data) {
	    if (g_Game.GetUIManager().GetMenu() != NULL) return;
	    super.OnStartClient(action_data);
        GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_START_BANK_RAID, null, true, action_data.m_Player.GetIdentity());
    }

    private bool isInNearOfBankAndLocationIsEnabled(PlayerBase playerWhoStartedRaid) {
        if (!playerWhoStartedRaid) {
            return false;
        }
        vector playerPosition = playerWhoStartedRaid.GetPosition();
        if (!playerPosition) {
            return false;
        }
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if (position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank){
                return position.raidIsEnabled;
            }
        }
        return false;
    }

};
