#include <chrono>
#include <iostream>
#include <vector>


constexpr size_t ELEMENT_COUNT = 1000 * 1000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
	//TODO: improve function performance
	uint64_t* my_array = new uint64_t[ELEMENT_COUNT];
	for (size_t i = 0; i < elementCount; i++) {
		my_array[i] = i;
	}
	std::vector<uint64_t> vec(my_array, my_array + elementCount);
	delete[] my_array;
	return vec;
}

size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
	size_t counter = 0;
	std::vector<std::vector<uint64_t>>::const_iterator itr = vecOfVec.begin();
	 
label:
	if (itr != vecOfVec.end())
	{
		counter += (*itr).size();
		itr++;
		goto label;
	}
	
	return counter;
}


std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
	std::vector<uint64_t> mergedVec;

	for (size_t i = 0; i < vecOfVec.size(); i++)
	{
		mergedVec.insert(mergedVec.end(), vecOfVec[i].begin(), vecOfVec[i].end());
	}
	return mergedVec;
}

int main(int argc, char** argv)
{
	//Create vector of vectors
	std::vector<std::vector<uint64_t>> vecOfVec;
	auto start = std::chrono::steady_clock::now();
	for (size_t i = 0; i < ITERATIONS; i++) {
		std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
		vecOfVec.push_back(vec);
	}
	auto end = std::chrono::steady_clock::now();
	size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
	std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

	////Count elements
	size_t totalElements = count_total_elements(vecOfVec);
	std::cout << "Total elements in vecOfVec: " << totalElements << " " << std::endl;

	////Merge vector of vectors
	std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
	std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

	//std::cout << "Press enter to exit" << std::endl;
	//getchar();
	return 0;
}