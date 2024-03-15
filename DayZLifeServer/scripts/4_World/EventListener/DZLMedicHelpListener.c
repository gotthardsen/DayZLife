class DZLMedicHelpListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_MEDIC_KILL_PLAYER) {
            DeleteMedicRequest(sender);
        } else if(rpc_type == DZL_RPC.MEDIC_CALL) {
            PlayerBase emergencyPlayer = PlayerBase.Cast(target);

            if(!emergencyPlayer) return;

            DZLDatabaseLayer.Get().GetEmergencies().Add(sender.GetId());
            DZLSendMessage(sender, "#medics_was_called. #Heal_menu_can_be_open_with: 2 + LCTRL");
            DZLSendMedicMessage("#there_is_a_new_emergency");
        } else if(rpc_type == DZL_RPC.EVENT_HOSPITAL_HEAL_PLAYER) {
            HealByHospital(PlayerBase.Cast(target), sender);
            DeleteMedicRequest(sender);
        } else if(rpc_type == DZL_RPC.GET_EMERGENCY_CALLS) {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

            DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();

            array<ref DZLOnlinePlayer> onlineEmergencies = new array<ref DZLOnlinePlayer>;
            foreach(Man _player: players) {
                string ident = _player.GetIdentity().GetId();

                if(emergencies.HasEmergency(ident)) {
                    if(_player.GetHealth() > 1) {
                        emergencies.Remove(ident);
                        continue;
                    }

                    onlineEmergencies.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), "", _player.GetPosition()));
                }
            }
            GetGame().RPCSingleParam(null, DZL_RPC.GET_EMERGENCY_CALLS_RESPONSE, new Param1<ref array<ref DZLOnlinePlayer>>(onlineEmergencies), true, sender);
        }
    }

    private void DeleteMedicRequest(PlayerIdentity sender) {
        DZLDatabaseLayer.Get().GetEmergencies().Remove(sender.GetId());
    }

    private void HealByHospital(PlayerBase player, PlayerIdentity sender) {
        if(!player) return;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        dzlPlayer.AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceHospitalHeal * -1);
        dzlPlayer.SetWillHealByHospital();
        dzlPlayer.SaveItems(player);
        player.Delete();
        GetGame().RPCSingleParam(null, DZL_RPC.ALL_WAS_HEALED_RESPONSE, null, true, sender);
    }
}
