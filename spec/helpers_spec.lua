dofile("MMOCoreORB/bin/scripts/utils/helpers.lua")

describe("filter", function()
	it("returns only items matching the predicate", function()
		local input = { 1, 2, 3, 4 }
		local result = filter(input, function(x)
			return x % 2 == 0
		end)

		assert.are.same({ 2, 4 }, result)
	end)

	it("returns an empty table when the predicate is false for all items", function()
		local input = { 1, 2, 3, 4 }
		local result = filter(input, function()
			return false
		end)

		assert.are.same({}, result)
	end)

	it("returns all items when the predicate is true for all items", function()
		local input = { 1, 2, 3, 4 }
		local result = filter(input, function()
			return true
		end)

		assert.are.same({ 1, 2, 3, 4 }, result)
	end)
end)
