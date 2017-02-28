#ifndef CAPTURE_H
#define CAPTURE_H

#include <ap_info.h>
#include <vector>


class Capture
{
public:
    Capture(std::string interface);
    void Start();
private:
   bool Loop(PDU& call_pdu);
   std::string interface;
   std::vector<AP_info*> ap_vec;
   void PrintAP();
   bool ExistAP(AP_info* ap);
};

#endif // CAPTURE_H
