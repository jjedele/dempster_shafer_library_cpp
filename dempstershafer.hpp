/*
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > library, definition
 */

#include <list>
#include <set>
#include <bitset>

/*
 * The MAX_HYPOTHESESES constant determines how many hypotheseses can be contained in the universe.
 */
#define MAX_HYPOTHESESES 64

using namespace std;

class DempsterShaferUniverse;
class Evidence;

typedef struct {
	double mass;
	bitset<MAX_HYPOTHESESES> items;
} FocalSet;

/**
 * This class represents the basic collection of all hypotheses and is used to
 * create evidences using those.
 */
class DempsterShaferUniverse {
	private:
		void* hypotheseses[MAX_HYPOTHESESES];
		int last_hypothesis_number;
	public:
		/**
		 * Simple Constructor
		 */
		DempsterShaferUniverse();
		/**
		 * Adds a set of pointers to arbitrary objects as hypotheseses. All other methods will
		 * need and return the same pointers that are added here.
		 *
		 * @param hypotheseses A reference to a set of pointers to arbitrary hypothesis objects.
		 */
		void add_hypotheseses(set<void*>& hypotheseses);
		/**
		 * Adds a set of pointers to arbitrary objects as hypotheseses. All other methods will
		 * need and return the same pointers that are added here.
		 *
		 * This var-arg version is a convenience wrapper for better readability when using hard-coded
		 * sets.
		 *
		 * @param hypothesis A list of pointers to arbitary hypothesis objects. The list MUST be terminated
		 * 		with NULL as sentinel value.
		 */
		void add_hypotheseses(void* hypothesis, ...);
		/**
		 * Creates and returns a new Evidence object. The sets must be added using the returned object.
		 * @return The new Evidence.
		 */
		Evidence add_evidence();
	friend class Evidence;
};

/**
 * This class represents a Evidence and is linked to the DempsterShaferUniverse it was created with.
 * All relevant operations are performed with these Evidence objects.
 */
class Evidence {
	private:
		DempsterShaferUniverse *universe;
		list<FocalSet> focal_sets;
		Evidence(DempsterShaferUniverse *universe);
		void add_focal_set(FocalSet set);
	public:
		/**
		 * Add a set of hypotheseses to the evidence and assign a mass to it.
		 * If not all mass is distributed to focal sets, add_omega_set() must be called to finish the evidence.
		 *
		 * @param mass The mass that is assigned to the set.
		 * @param members The set of pointers to the hypotheseses. Must be the same pointers that were added to the universe.
		 */
		void add_focal_set(double mass, set<void*>& members);
		/**
		 * Add a set of hypotheseses to the evidence and assign a mass to it.
		 * var-arg version for convenience.
		 * If not all mass is distributed to focal sets, add_omega_set() must be called to finish the evidence.
		 *
		 * @param mass The mass that is assigned to the set.
		 * @param member A list of pointers to the hypotheseses. Must be the same pointers that were added to the universe.
		 * 		The list MUST be terminated with NULL as sentinel value.
		 */
		void add_focal_set(double mass, void *member, ...);
		/**
		 * Adds the omega set to the evidence if the entire mass is not distributed already.
		 */
		void add_omega_set();
		/**
		 * Overrides the & operator to combine two evidences. Conflicts are resolved automatically.
		 */
		Evidence operator&(Evidence& other);
		/**
		 * Calculates the conflict between two evidences.
		 *
		 * @param other A reference to the second evidence.
		 * @return The calculated conflict.
		 */
		double conflict(Evidence& other);
		/**
		 * Calculates the belief for a set of hypotheseses.
		 *
		 * @param members A reference to a set of hypothesis object pointers.
		 * @return The calculated belief.
		 */
		double belief(set<void*>& members);
		/**
		 * Calculates the belief for a list of hypotheseses.
		 * Var-arg version for convenience.
		 *
		 * @param member A list of pointers to hypothesis objects.
		 * 		The list must be terminated with NULL as sentinel value.
		 * @return The calculated belief.
		 */
		double belief(void *member, ...);
		/**
		 * Calculates the plausability for a set of hypotheseses.
		 *
		 * @param members A reference to a set of hypothesis object pointers.
		 * @return The calculated plausability.
		 */
		double plausability(set<void*>& members);
		/**
		 * Calculates the plausability for a list of hypotheseses.
		 * Var-arg version for convenience.
		 *
		 * @param member A list of pointers to hypothesis objects.
		 * 		The list must be terminated with NULL as sentinel value.
		 * @return The calculated plausability.
		 */
		double plausability(void *member, ...);
		/**
		 * Searches and returns the single hypothesis with the largest belief.
		 * If several hypotheseses with the same belief are found, an arbitrary one is returned.
		 *
		 * @return A pointer to the most believable hypothesis object.
		 */
		void* most_believable();
		/**
		 * Searches and returns the single hypothesis with the largest plausability.
		 * If several hypotheseses with the same plausability are found, an arbitrary one is returned.
		 *
		 * @return A pointer to the most plausible hypothesis object.
		 */
		void* most_plausible();
		/**
		 * Prints a human readable representation of the evidence to the standard output.
		 *
		 * @param hypothesis_to_string A pointer to a function that receives a pointer to a hypothesis object and returns
		 * 		a string representation for it.
		 */
		void pretty_print(string (*hypothesis_to_string)(void *element));
	friend class DempsterShaferUniverse;
};
