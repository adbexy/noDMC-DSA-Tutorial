#pragma once

#include <dml/dml.hpp>

inline const std::string status_code_to_string(const dml::status_code code) {
	switch(code) {
		case dml::status_code::ok:						return "ok";
		case dml::status_code::false_predicate:			return "false predicate";
		case dml::status_code::partial_completion:		return "partial completion";
		case dml::status_code::nullptr_error:			return "nullptr error";
		case dml::status_code::bad_size:				return "bad size";
		case dml::status_code::bad_length:				return "bad length";
		case dml::status_code::inconsistent_size:		return "inconsistent size";
		case dml::status_code::dualcast_bad_padding:	return "dualcast bad padding";
		case dml::status_code::bad_alignment:			return "bad alignment";
		case dml::status_code::buffers_overlapping:		return "buffers overlapping";
		case dml::status_code::delta_delta_empty:		return "delta delta empty";
		case dml::status_code::batch_overflow:			return "batch overflow";
		case dml::status_code::execution_failed:		return "execution failed";
		case dml::status_code::unsupported_operation:	return "unsupported operation";
		case dml::status_code::queue_busy:				return "queue busy";
		case dml::status_code::error:					return "unknown error";
		case dml::status_code::config_error:			return "config error";
		default: return "unhandled error";
	}
}
