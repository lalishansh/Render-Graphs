#include <fmt/core.h>

import RenderGraph;

template<typename... T> requires (sizeof...(T) > 0) struct Input {
	std::tuple<T...>        data;
	static constexpr size_t NumOfEntries = std::tuple_size_v<decltype (data)>;
	const char*             entries[NumOfEntries];

	template<typename AppendTyp> requires std::is_trivial_v<AppendTyp>
	[[nodiscard]] constexpr auto add (const char* name, AppendTyp default_value) {
		Input<T..., AppendTyp> new_input;
		std::memcpy (&std::get<0> (new_input.data), &std::get<0> (data), sizeof (data));
		std::memcpy (&std::get<NumOfEntries> (new_input.data), &default_value,
					 sizeof (default_value));
		std::memcpy (new_input.entries, entries, sizeof (entries));
		new_input.entries[NumOfEntries] = name;
		return new_input;
	}
};

template<typename... T> struct Output: Input<T...>
{
	Output ()
	  : Input<T...> () {}
	Output (Input<T...> input)
	  : Input<T...> (input) {}
};

template<typename Input_t = std::nullptr_t, typename Output_t = std::nullptr_t> class NodeCreator
{
  public:
	NodeCreator ()
	  : input{}
	  , output{} {}

  public: // This is a workaround for the compiler error cannot access private member
		  // declared in different template specialized class
	Input_t  input;
	Output_t output;

	NodeCreator (const Input_t input, const Output_t output)
	  : input (input)
	  , output (output) {}

  public:
	template<typename Typ>
	[[nodiscard]] constexpr auto addInput (const char* name, Typ default_value) {
		if constexpr (std::is_same_v<Input_t, std::nullptr_t>) {
			Input<Typ> new_input;
			std::get<0> (new_input.data) = default_value;
			new_input.entries[0]         = name;
			return NodeCreator<Input<Typ>, Output_t> (new_input, output);
		} else {
			const Input new_input = input.add (name, default_value);
			return NodeCreator<std::remove_const_t<decltype(new_input)>, Output_t> (new_input, output);
		}
	}

	template<typename Typ>
	[[nodiscard]] constexpr auto addOutput (const char* name, Typ default_value) {
		if constexpr (std::is_same_v<Output_t, std::nullptr_t>) {
			Output<Typ> new_output;
			std::get<0> (new_output.data) = default_value;
			new_output.entries[0]         = name;
			return NodeCreator<Input_t, Output<Typ>> (input, new_output);
		} else {
			const auto new_output = output.add (name, default_value);
			return NodeCreator<Input_t, std::remove_const_t<decltype(new_output)>> (input, new_output);
		}
	}
};

extern "C" int EntryPoint (int, char**) {
	auto node = NodeCreator<>()
					 .addInput ("test", 1)
					 .addOutput ("test2", 2)
					 .addInput ("test3", 3)
					 .addOutput ("test4", 4);
	(void)node;
	return 0;
}
