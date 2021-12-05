fn part2<const N: usize>(input: &[String]) -> Result<usize, Box<dyn Error>> {
    macro_rules! rating {
        ($cmp:tt) => {{
            let mut clone = input.iter().collect::<Vec<_>>();
            for idx in 0..N {
                let mut sum = 0;
                for c in clone.iter() {
                    if c.as_bytes().iter().nth(idx) == Some(&b'1') {
                        sum += 1;
                    }
                }

                let ch = if sum $cmp clone.len() / 2 {
                    b'1'
                } else {
                    b'0'
                };

                clone.retain(|&s| s.as_bytes()[idx] == ch);
                if clone.len() == 1 {
                    break;
                }
            }

            clone
        }};
    }

    let oxygen = rating!(>=);
    let co2 = rating!(<);

    if oxygen.len() != 1 || co2.len() != 1 {
        return Err("Lengths not 1".into());
    }

    Ok(usize::from_str_radix(oxygen[0], 2)? * usize::from_str_radix(co2[0], 2)?)
}
