#pragma once
#include <fstream>
#include <Windows.h>

typedef char message[20];

class blocking_circular_file_buffer {
protected:
	static constexpr const char* data_semaphore_name = "DataSemaphore";
	static constexpr const char* space_semaphore_name = "SpaceSemaphore";
	static constexpr const char* file_mutex_name = "FileMutex";
	static constexpr int header_offset = 3 * sizeof(int);
	static constexpr int n_records_offset = 0;
	static constexpr int read_count_offset = sizeof(int);
	static constexpr int write_count_offset = 2 * sizeof(int);
	std::fstream& file_;

	void set_read_count(int read_count) const;
	void set_write_count(int write_count) const;
	void set_n_records(int n_records) const;
	int get_n_records() const;

private:
	HANDLE data_available_;
	HANDLE space_available_;
	HANDLE file_mutex_;

	int get_read_count() const;
	int get_write_count() const;

public:

	blocking_circular_file_buffer(const blocking_circular_file_buffer& b) = delete;
	blocking_circular_file_buffer(blocking_circular_file_buffer&& b) = delete;
	blocking_circular_file_buffer& operator=(blocking_circular_file_buffer b) = delete;
	blocking_circular_file_buffer& operator=(blocking_circular_file_buffer&& b) = delete;

	blocking_circular_file_buffer(
		std::fstream& file,
		HANDLE data_available,
		HANDLE space_available,
		HANDLE file_mutex);

	std::string pop() const;

	void push(message m) const;

	virtual ~blocking_circular_file_buffer();
};
