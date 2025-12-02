local ok, m = pcall(require, "mylib")
if not ok then
  print("Failed to require mylib:", m)
  os.exit(1)
end

print(m.hello("Lua"))
