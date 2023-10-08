func fill(maze [][]int) {
	var n int
	for y := 0; y < len(maze); y++ {
		for x := 0; x < len(maze[y]); x++ {
			n = 0
			if maze[y][x] != -1 {
				if y > 0 && maze[y-1][x] == -1 {
					n++
				}
				if y > 0 && x < len(maze[y])-1 && maze[y-1][x+1] == -1 {
					n++
				}
				if x < len(maze[y])-1 && maze[y][x+1] == -1 {
					n++
				}
				if y < len(maze)-1 && x < len(maze[y])-1 && maze[y+1][x+1] == -1 {
					n++
				}
				if y < len(maze)-1 && maze[y+1][x] == -1 {
					n++
				}
				if y < len(maze)-1 && x > 0 && maze[y+1][x-1] == -1 {
					n++
				}
				if x > 0 && maze[y][x-1] == -1 {
					n++
				}
				if y > 0 && x > 0 && maze[y-1][x-1] == -1 {
					n++
				}
				maze[y][x] = n
			}
		}
	}
}