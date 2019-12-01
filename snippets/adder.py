def adder():
  def merge(a,b):
      res = a[::]
      res.extend(b)
      return sorted(res)
      
  def add(a,x):
      num_ops = 0
      v = [x]
      i = 0
      while len(a[i]) > 0:
          num_ops += len(v) + len(a[i])
          v = merge(v,a[i])
          a[i] = []
          i += 1
      a[i] = v
      return num_ops
      
  for t in range(10):
    a = [list() for i in range(100)]
    s = 0
    for i in range(2**t):
        s += add(a,i)
    print(t,s)

adder()