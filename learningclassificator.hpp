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
		 */
		int add_feature(double initial_average);
		/**
		 * Classify a value and adjust the average used to classify.
		 *
		 * @param feature Index of the feature to use.
		 * @param value The value to classify.
		 * @return The relation to the average of values. May reach from -1.0 (<= 50% of average) to +1.0 (>=200% of average).
		 */
		double classify(int feature, double value);
};
