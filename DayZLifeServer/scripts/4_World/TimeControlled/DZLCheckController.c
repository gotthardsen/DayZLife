class DZLCheckController {

    void Check() {
        DZLConfig config = DZLConfig.Get();
        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);
        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            if(!player) continue;
            PlayerIdentity playerIdent = player.GetIdentity();

            DZLPayCheck.Check(player, config.jobConfig.paycheck);
        }
        DZLInsuranceManager.Get().Check();
    }
}
