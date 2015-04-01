#include <string>
using std::string;

class Character {
	public:
		Character(string name = "", string job = "", int level = 1, int exp = 0, int money = 1, int str = 1, int def = 1, int mag = 1, int agi = 1){
			m_name=name;
			m_job=job;
			m_level=level;
			m_exp=exp;
			m_money=money;
			m_str=str;
			m_def=def;
			m_mag=mag;
			m_agi=agi;
		}
	
		string get_name() {return m_name;}
		void set_name(string name) {m_name=name;}
		string get_job() {return m_job;}
		void set_job(string job) {m_job=job;}	
		int get_level() {return m_level;}
		void set_level(int level) {m_level=level;}
		int get_exp() {return m_exp;}
		void set_exp(int exp) {m_exp=exp;}	
		int get_money() {return m_money;}
		void set_money(int money) {m_money=money;}
		int get_str() {return m_str;}
		void set_str(int str) {m_str=str;}
		int get_def() {return m_def;}
		void set_def(int def) {m_def=def;}
		int get_mag() {return m_mag;}
		void set_mag(int mag) {m_mag=mag;}
		int get_agi() {return m_agi;}
		void set_agi(int agi) {m_agi=agi;}
		
	
	private:
		string m_name;
		string m_job;
		int m_level;
		int m_exp;
		int m_money;
		int m_str;
		int m_def;
		int m_mag;
		int m_agi;	
};

struct Attributes
{
    int base_STR;
    int scaling_STR;
    int base_DEF;
    int scaling_DEF;
    int base_MAG;
    int scaling_MAG;
    int base_AGI;
    int scaling_AGI;
    string general_desc;
	string passive1_desc;
	string passive2_desc;
    
	Attributes(int str=0, int upstr=0, int def=0, int updef=0, int mag=0, int upmag=0, int agi=0, int upagi=0, string gendesc="", string passive1desc="", string passive2desc="") {
	    this->base_STR = str;
	    this->scaling_STR = upstr;
	    this->base_DEF = def;
	    this->scaling_DEF = updef;
	    this->base_MAG = mag;
	    this->scaling_MAG = upmag;
	    this->base_AGI = agi;
	    this->scaling_AGI = upagi;
	    this->general_desc = gendesc;
	    this->passive1_desc = passive1desc;
	    this->passive2_desc = passive2desc;
	}
};

typedef std::map<string, Attributes> JobList;
JobList g_jobs;


Character create_new_character(string name, string job)
{
    Character ch;
    ch.set_name(name);
    ch.set_job(job);
    ch.set_level(1);
    ch.set_exp(0);
    ch.set_money(0);

    JobList::iterator it_joblist;

    for (it_joblist = g_jobs.begin(); it_joblist != g_jobs.end(); ++it_joblist) {
        if (it_joblist->first == job) {
            ch.set_str(it_joblist->second.base_STR);
            ch.set_def(it_joblist->second.base_DEF);
            ch.set_mag(it_joblist->second.base_MAG);
            ch.set_agi(it_joblist->second.base_AGI);
            break;
        }
    }
    return ch;
}
