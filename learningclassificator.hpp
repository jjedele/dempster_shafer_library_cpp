/*
 * Dempster-Shafer Library for Evidence-Theory
 * Thilo Michael, Jeffrey Jedele
 * 2012
 * > classificator, definition
 */

/**
 * The LearningClassificator can be used to classify a set of numeric features with regard to how thy relate to their average.
 * It uses online learning to adjust the used average with the classified values.
 */
class LearningClassificator {
	private:
		double learning_rate;
		int maximum_index;
		int current_index;
		double *first_feature_average;
	public:
		/**
		 * Constructor.
		 *
		 * @param learning_rate Determines how fast the stores averages are adjusted. Must be between 0.0 and 1.0.
		 * @param size The maximum amount of features that can be stored.
		 * @throws 1 if learning rate is not between 0.0 and 1.0
		 * @throws 2 if size is < 1
		 */
		LearningClassificator(double learning_rate, int size);
		/**
		 * Destructor-
		 */
		~LearningClassificator();
		/**
		 * Add a feature and set the initial average value used for classifying it.
		 *
		 * @param initial_average The initial average value used for classifying.
		 * @return The index of the new feature.
		 * @throws 1 if the classificator can't hold more features
		 */
		int add_feature(double initial_average);
		/**
		 * Classify a value and adjust the average used to classify.
		 *
		 * @param feature Index of the feature to use.
		 * @param value The value to classify.
		 * @return The relation to the average of values. Reaches from -1.0 for far below average to 1.0 for far above average.
		 * @throws 1 if the chosen feature does not exist.
		 */
		double classify(int feature, double value);
};
