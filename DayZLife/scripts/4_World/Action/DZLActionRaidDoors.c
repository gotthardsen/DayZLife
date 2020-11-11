class DZLActionRaidDoors: ActionInteractBase
{
    ref DZLHouseConfig config;

	void DZLActionRaidDoors() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.OpenDoors;

        if (GetGame().IsServer()) {
            config = new DZLHouseConfig();
        }
	}

	override string GetText(){
		return "#break_door";
	}
	
	override void CreateConditionComponents()
	{	
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
	    if (GetGame().IsClient() && (!player.config || !player.config.houseConfig)) return false;

		if(GetGame().IsClient()){
			config = player.config.houseConfig;
		}

		Building building = Building.Cast(target.GetObject());

		if (!building) return false;

		if(building.IsBuilding()) {
		   	DZLHouseDefinition definition = config.GetHouseDefinitionByBuilding(building);
			if (!definition) return false;
			
			item = player.GetItemInHands();
		   
			foreach(string itemType: definition.raidTools) {
				if (item.GetType() == itemType) {
					if (GetGame().IsServer() && item.GetHealth() < 50) {
                        return false;
					}

					int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
					if (doorIndex != -1) {
						if (GetGame().IsServer()) {
							DZLHouse dzlHouse = new DZLHouse(building);
							return !building.IsDoorOpen(doorIndex) && dzlHouse && dzlHouse.CanRaidDoor(player, doorIndex);
						}
						
						return !building.IsDoorOpen(doorIndex);
					}
				}
			}
		}
		
		return false;
	}

	override void OnEndClient(ActionData action_data) {
		Building buildingClient = Building.Cast(action_data.m_Target.GetObject());
		DZLDoorRaidProgressBar bar = action_data.m_Player.GetRaidProgressBar();
		
		int doorIndex = buildingClient.GetDoorIndex(action_data.m_Target.GetComponentIndex());
		if (doorIndex != -1) {
			bar.SetBuilding(buildingClient, doorIndex);
			DZLHouseDefinition definition = config.GetHouseDefinitionByBuilding(buildingClient);
			if (definition) {
				bar.SetMaxRange(definition.raidRange);
				bar.SetRaidItem(action_data.m_MainItem);
				GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR, new Param2<PlayerBase, Building>(action_data.m_Player, buildingClient), true);
				GetGame().GetUIManager().ShowScriptedMenu(bar, NULL);
			}
		}
	}
	

};