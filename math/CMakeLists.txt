if (BUILD_TESTS)
	target_sources(tests PRIVATE
		test_helper.h test_helper.cpp
		mat_test_helper.h
		matrix_test.cpp
		trans_mat_test.cpp
	)
endif()
