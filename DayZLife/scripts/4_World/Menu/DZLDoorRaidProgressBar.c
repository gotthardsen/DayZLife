class DZLDoorRaidProgressBar: DZLBaseProgressBar
{
    private Building building;
    private int doorIndex;
	private EntityAI item;

	override Widget Init() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		
		return super.Init();
    }

    void SetBuilding(Building building, int doorIndex) {
        this.building = building;
        this.doorIndex = doorIndex;

        duration = 999999999999999;
        maxRange = 10;
        position = building.GetPosition();
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR_RESPONSE) {
            autoptr Param1<DZLHouse> paramRaidDoorResponse;
            if (ctx.Read(paramRaidDoorResponse)){
                SetDuration(paramRaidDoorResponse.param1.raidTime);
            }
        }
    }
	
	void SetRaidItem(EntityAI item) {
		this.item = item;
	}

	override void OnHide() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
		
		super.OnHide();
	}
	
	override void SendFinishEvent() {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_RAID_DOOR, new Param4<PlayerBase, Building, int, EntityAI>(player, building, doorIndex, item), true);
    }
}
