#include "capture.h"

Capture::Capture(std::string interface)
{
    this->interface = interface;
}

void Capture::Start()
{
    SnifferConfiguration sconf;
    sconf.set_rfmon(true);
    Sniffer sniffer(this->interface, sconf);

    std::cout << "Start-----------------------------------------" << std::endl;
    sniffer.sniff_loop(make_sniffer_handler(this, &Capture::Loop));
}

bool Capture::Loop(PDU& pdu)
{
    AP_info* ap_info = new AP_info();
    try
    {
        const RadioTap& radiotap = pdu.rfind_pdu<RadioTap>();
        const Dot11ManagementFrame& dotmgf = pdu.rfind_pdu<Dot11ManagementFrame>();

        if(!dotmgf.from_ds() && !dotmgf.to_ds())
        {
            if(radiotap.present() & RadioTap::DBM_SIGNAL)
            {
                ap_info->SetPwr((int)radiotap.dbm_signal());
            }
            std::cout << (int)dotmgf.subtype() << std::endl;

            switch (dotmgf.subtype()) {
            case Dot11ManagementFrame::BEACON:
                ap_info->SetBssid(dotmgf);                  // setting bssid
                ap_info->SetChannel(dotmgf);                // setting channel
                ap_info->SetEssid(dotmgf);                  // setting essid
                ap_info->SetEncrypt(dotmgf);                // setting Encrypt, Cipher
                ap_info->SetAuth(dotmgf);                   // setting Auth
                ap_info->SetMB(dotmgf);                     // setting MB
                break;
            default:
                break;
            }
        }
    }
    catch(pdu_not_found)
    {
    }

    if(!ExistAP(ap_info))
    {
        this->ap_vec.push_back(ap_info);
    }
    PrintAP();
    return true;
}

bool Capture::ExistAP(AP_info* ap)
{
    bool status = false;
    for(AP_info* a_vec : this->ap_vec)
    {
        if(a_vec->GetBssid() == ap->GetBssid())
        {
            a_vec->IncreCnt();
            a_vec->SetPwr(ap->GetPwr());
            status = true;
            break;
        }
    }
    return status;
}

void Capture::PrintAP()
{
    std::system("clear");
    std:: cout << "BSSID\t\t\t PWR\t BEACONS\t CHANNEL\t MB\t ENC\t CIPHER\t AUTH\t ESSID\n" << std::endl;
    for(AP_info* ap : this->ap_vec)
    {
        if(ap->GetEssid() == "")
            continue;
        std::cout << ap->GetBssid() << "\t";
        std::cout << ap->GetPwr() << "\t ";
        std::cout << ap->GetCnt() << "\t\t ";
        std::cout << (int)ap->GetChannel() << "\t\t ";
        std::cout << ap->GetMB() << "\t ";
        std::cout << ap->GetEnc() << "\t ";
        std::cout << ap->GetCipher() << "\t ";
        std::cout << ap->GetAuth() << "\t ";
        std::cout << ap->GetEssid() << std::endl;
    }
}
