/**
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > library, definition
 */

#include <list>
#include <set>
#include <bitset>
#define MAX_HYPOTHESESES 64

using namespace std;

class DempsterShaferUniverse;
class Evidence;

typedef struct {
	double mass;
	bitset<MAX_HYPOTHESESES> items;
} FocalSet;

class DempsterShaferUniverse {
	private:
		void* hypotheseses[MAX_HYPOTHESESES];
		int last_hypothesis_number;
	public:
		DempsterShaferUniverse();
		void add_hypotheseses(set<void*>& hypotheseses);
		void add_hypotheseses(void* hypothesis, ...);
		Evidence add_evidence();
	friend class Evidence;
};

class Evidence {
	private:
		DempsterShaferUniverse *universe;
		list<FocalSet> focal_sets;
		Evidence(DempsterShaferUniverse *universe);
		void add_focal_set(FocalSet set);
	public:
		void add_focal_set(double mass, void *member, ...);
		void add_focal_set(double mass, set<void*>& members);
		void add_omega_set();
		Evidence operator&(Evidence& other);
		double conflict(Evidence& other);
		double belief(set<void*>& members);
		double belief(void *member, ...);
		double plausability(void *member, ...);
		double plausability(set<void*>& members);
		void* most_believable();
		void* most_plausible();
		void pretty_print(string (*hypothesis_to_string)(void *element));
	friend class DempsterShaferUniverse;
};
