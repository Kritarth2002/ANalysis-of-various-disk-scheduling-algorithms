#include <bits/stdc++.h>
using namespace std;

int uniform(int, int);
int scan(int, int[], int[], int);
int cscan(int, int[], int[], int);
int fifo(int, int[], int[], int);
int sstf(int, int[], int[], int);

int main()
{
    int ini_HeadLocation = 5000 / 2;  // initial head location
    int scanSeekTimeAvg = 0, cscanSeekTimeAvg = 0;
    int fifoSeekTimeAvg = 0, sstfSeekTimeAvg = 0;

    for (int i = 0; i < 10; i++)
    {
        int req = uniform(500, 1000);
        int req_Tracks[req];
        int req_Sectors[req];
        for (int y = 0; y < req; y++)
        {
            req_Tracks[y] = uniform(0, 5000);
            req_Sectors[y] = uniform(0, 12000);
        }

        cout << "Number of req: " << req << endl;

        scanSeekTimeAvg += scan(req, req_Tracks, req_Sectors, ini_HeadLocation);
        cout << "Scan Avg Seek " << i + 1 << " :" << scan(req, req_Tracks, req_Sectors, ini_HeadLocation) << endl;

        cscanSeekTimeAvg += cscan(req, req_Tracks, req_Sectors, ini_HeadLocation);
        cout << "cScan Avg Seek " << i + 1 << " :" << cscan(req, req_Tracks, req_Sectors, ini_HeadLocation) << endl;

        fifoSeekTimeAvg += fifo(req, req_Tracks, req_Sectors, ini_HeadLocation);
        cout << "Fifo Avg Seek " << i + 1 << " :" << scan(req, req_Tracks, req_Sectors, ini_HeadLocation) << endl;

        sstfSeekTimeAvg += sstf(req, req_Tracks, req_Sectors, ini_HeadLocation);
        cout << "SSTF Avg Seek " << i + 1 << " :" << sstf(req, req_Tracks, req_Sectors, ini_HeadLocation) << endl;

        cout << "*************" << endl;
    }

    cout << "Scan Overall Avg Seek Time: " << scanSeekTimeAvg/10 << endl;
    cout << "cScan Overall Avg Seek Time: " << cscanSeekTimeAvg/10 << endl;
    cout << "Fifo Overall Avg Seek Time: " << fifoSeekTimeAvg/10 << endl;
    cout << "SSTF Overall Avg Seek Time: " << sstfSeekTimeAvg/10 << endl;

    return 0;
}
// uniform random value
int uniform(int min, int max)
{
    int random = rand()%(max-min+1) + min;
    return random;
}

//scan search
int scan(int req, int req_Tracks[], int req_Sectors[], int ini_HeadLocation)
{

    vector<int> tempTrack_h;
    vector<int> tempTrack_l;

    for (int i = 0; i < req; i++)
    {
        if (req_Tracks[i] >= ini_HeadLocation)
        {
            tempTrack_h.push_back(req_Tracks[i]);
        }
        else
        {
            tempTrack_l.push_back(req_Tracks[i]);
        }
    }
    int size1 = tempTrack_h.size();
    int size2 = tempTrack_l.size();
    vector<int> mergedTracks(req);

    sort(tempTrack_h.begin(), tempTrack_h.end());
    sort(tempTrack_l.begin(), tempTrack_l.end(), greater<int>());

    for (int i = 0; i < size1; i++)

    {
        mergedTracks[i] = tempTrack_h[i];
    }
    int mergeSize = mergedTracks.size();

    int x = 0;
    for (int i = size1; i < mergeSize; i++)
    {
        mergedTracks[i] = tempTrack_l[x];
        x++;
    }


    vector<int> tracksTraversed(req);// sectors traversed = sectors
    vector<int> seekTimes(req);

    for (int i = 0; i < size1; i++) {

            tracksTraversed[i] = tempTrack_h[i + 1] - tempTrack_h[i];
    }
    for (int i = 0; i < size2; i++)
    {
            tracksTraversed[i + size1] = tempTrack_l[i] - tempTrack_l[i + 1];
    }

    for (int i = 0; i < req; i++) // for each req tracks
    {
        seekTimes[i] = tracksTraversed[i] + req_Sectors[i];
    }
    long seekTimeAverage = 0;

    for (int i = 0; i < req; i++)
    {
        seekTimeAverage += seekTimes[i];
    }

    if (req != 0)
    {
        seekTimeAverage = seekTimeAverage / req;
    }
    else
    {
        cout << "No requests" << endl;
    }
    return seekTimeAverage;
}

// cscan search

int cscan(int req, int req_Tracks[], int req_Sectors[], int ini_HeadLocation)
{
    vector<int> tempTrack_h;
    vector<int> tempTrack_l;

    for (int i = 0; i < req; i++)
    {
        if (req_Tracks[i] >= ini_HeadLocation)
        {
            tempTrack_h.push_back(req_Tracks[i]);
        }
        else
        {
            tempTrack_l.push_back(req_Tracks[i]);
        }
    }

    int size1 = tempTrack_h.size();
    int size2 = tempTrack_l.size();
    vector<int> mergedTracks(req);

    sort(tempTrack_h.begin(), tempTrack_h.end());
    sort(tempTrack_l.begin(), tempTrack_l.end());

    for (int i = 0; i < size1; i++)
    {
        mergedTracks[i] = tempTrack_h[i];
    }

    int x = 0;
    int mergedSize = mergedTracks.size();

    for (int i = size1; i < mergedSize; i++)
    {
        mergedTracks[i] = tempTrack_l[x];
        x++;
    }

    vector<int> tracksTraversed(req);
    vector<int> seekTimes(req);

    for (int i = 0; i < size1; i++)
    {
        if (i != size1)
        {
            tracksTraversed[i] = tempTrack_h[i + 1] - tempTrack_h[i];
        }
    }

    for (int i = 0; i < size2; i++)
    {
        if (i != size2)
        {
            tracksTraversed[i + size1] = tempTrack_l[i + 1] - tempTrack_l[i];
        }
    }

    for (int i = 0; i < req; i++)
    {
        seekTimes[i] = tracksTraversed[i] + req_Sectors[i]; // sectors traversed = sectors
    }
    long seekTimeAvg = 0;

    for (int i = 0; i < req; i++)
    {
        seekTimeAvg += seekTimes[i];
    }

    if (req != 0)
    {
        seekTimeAvg = seekTimeAvg / req;
    }
    else
    {
        cout << "No requests" << endl;
    }
    return seekTimeAvg;
}

//fifo search
int fifo(int req, int req_Tracks[], int req_Sectors[], int ini_HeadLocation)
{
    vector<int> tempTrack(req);
    vector<int> tracksTraversed(req);
    vector<int> seekTime(req);
    for (int i = 0; i < req; i++) {
        tempTrack[i] = req_Tracks[i];
    }

    for (int i = 0; i < req; i++)
    {
      tracksTraversed[i] = abs(tempTrack[i] - tempTrack[i + 1]);
    }

    for (int i = 0; i < req; i++)
    {
        seekTime[i] = tracksTraversed[i] + req_Sectors[i];
    }
    long seekTimeAverage = 0;

    for (int i = 0; i < req; i++)
    {
        seekTimeAverage += seekTime[i];
    }

    if (req != 0)
    {
        seekTimeAverage = seekTimeAverage / req;
    }
    else
    {
        cout << "No requests" << endl;
    }
    return seekTimeAverage;
}

//sstf search
int sstf(int req, int req_Tracks[], int req_Sectors[], int ini_HeadLocation)
{
    vector<int> tempTrack(req);
    vector<int> tracksTraversed(req);
    for (int i = 0; i < req; i++)
    {
        tempTrack[i] = req_Tracks[i];
    }
    int count=0;
    int initial=ini_HeadLocation;

    while(count!=req)
    {
        int min=5000,diff,index;
        for(int i=0;i<req;i++)
        {
           diff=abs(tempTrack[i]-initial);
           if(min>diff)
           {
               min=diff;
               index=i;
           }

        }
        tracksTraversed[count]=min;
        initial=tempTrack[index];
        tempTrack[index]=INT_MAX;
        count++;
    }
    vector<int> seekTime(req);

    for (int i = 0; i < req; i++)
    {
        seekTime[i] = tracksTraversed[i] + req_Sectors[i];
    }

    long seekTimeAvg = 0;

    for (int i = 0; i < req; i++)
    {
        seekTimeAvg += seekTime[i];}

    if (req != 0)
    {
        seekTimeAvg = seekTimeAvg / req;
    }
    else
    {
        cout << "No requests" << endl;
    }
    return seekTimeAvg;
}
