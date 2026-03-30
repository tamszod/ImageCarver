#pragma once

namespace crv {
	namespace helper {

		/* @brief Normalize the rotation degree to be within [0, 360).
		 * 
		 * @param degree The rotation degree to be normalized. "degree" is modified in-place.
		 * 
		 * @return void
		 */
		void NormalizeRotationDegree(float& degree);
	}
}