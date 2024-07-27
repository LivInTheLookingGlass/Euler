use std::cmp::max;

pub fn reduce_triangle(triangle: Vec<Vec<u8>>) -> u16 {
    let centering = triangle
        .last()
        .expect("Given vector must have at least one element")
        .len() + 1;
    let mut potential_totals: Vec<u16> = vec![0; centering];
    for parent in triangle.iter().rev() {
        for i in 0..(parent.len()) {
            potential_totals[i] = max(potential_totals[i], potential_totals[i + 1]) + parent[i] as u16;
        }
    }
    return potential_totals[0];
}