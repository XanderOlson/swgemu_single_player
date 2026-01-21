require("utils.helpers")

describe("map", function()
	it("converts values with the provided function", function()
		local result = map({ 1, 2, 3 }, function(value)
			return value * 2
		end)

		assert.same({ 2, 4, 6 }, result)
	end)

	it("returns an empty table when given an empty table", function()
		local result = map({}, function(value)
			return value * 2
		end)

		assert.same({}, result)
	end)
end)
