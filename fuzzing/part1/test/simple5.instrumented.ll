; ModuleID = 'simple5.ll'
source_filename = "simple5.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !7 {
entry:
  %retval = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  %un = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %y, metadata !11, metadata !DIExpression()), !dbg !12
  store i32 1, i32* %y, align 4, !dbg !12
  call void @llvm.dbg.declare(metadata i32* %z, metadata !13, metadata !DIExpression()), !dbg !14
  store i32 1, i32* %z, align 4, !dbg !14
  call void @llvm.dbg.declare(metadata i32* %un, metadata !15, metadata !DIExpression()), !dbg !16
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %un), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %x, metadata !18, metadata !DIExpression()), !dbg !19
  %0 = load i32, i32* %un, align 4, !dbg !20
  %add = add nsw i32 %0, 1, !dbg !21
  store i32 %add, i32* %x, align 4, !dbg !19
  %1 = load i32, i32* %y, align 4, !dbg !22
  %2 = load i32, i32* %x, align 4, !dbg !23
  call void @__dbz_sanitizer__(i32 %2, i32 8, i32 9)
  %div = sdiv i32 %1, %2, !dbg !24
  store i32 %div, i32* %z, align 4, !dbg !25
  ret i32 0, !dbg !26
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @__isoc99_scanf(i8*, ...) #2

declare void @__dbz_sanitizer__(i32, i32, i32)

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 8.0.0-3~ubuntu18.04.1 (tags/RELEASE_800/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, nameTableKind: None)
!1 = !DIFile(filename: "simple5.c", directory: "/home/cs6340/fuzzing/fuzzing/part1/test")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 8.0.0-3~ubuntu18.04.1 (tags/RELEASE_800/final)"}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DILocalVariable(name: "y", scope: !7, file: !1, line: 4, type: !10)
!12 = !DILocation(line: 4, column: 7, scope: !7)
!13 = !DILocalVariable(name: "z", scope: !7, file: !1, line: 4, type: !10)
!14 = !DILocation(line: 4, column: 14, scope: !7)
!15 = !DILocalVariable(name: "un", scope: !7, file: !1, line: 5, type: !10)
!16 = !DILocation(line: 5, column: 7, scope: !7)
!17 = !DILocation(line: 6, column: 3, scope: !7)
!18 = !DILocalVariable(name: "x", scope: !7, file: !1, line: 7, type: !10)
!19 = !DILocation(line: 7, column: 7, scope: !7)
!20 = !DILocation(line: 7, column: 11, scope: !7)
!21 = !DILocation(line: 7, column: 14, scope: !7)
!22 = !DILocation(line: 8, column: 7, scope: !7)
!23 = !DILocation(line: 8, column: 11, scope: !7)
!24 = !DILocation(line: 8, column: 9, scope: !7)
!25 = !DILocation(line: 8, column: 5, scope: !7)
!26 = !DILocation(line: 9, column: 3, scope: !7)